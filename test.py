import unittest
import os
import subprocess

class TestDatabase(unittest.TestCase):
    def setUp(self):
        try:
            os.remove('test.db')
        except OSError:
            pass

    def run_script(self, commands):
        process = subprocess.Popen(["./db", "mydb.db"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        output, _ = process.communicate(input="\n".join(commands).encode())
        return output.decode().split("\n")

    def test_insert_retrieve(self):
        result = self.run_script([
            "insert 1 user1 person1@example.com",
            "select",
            ".exit",
        ])
        self.assertEqual(result, [
            "db > Executed.",
            "db > (1, user1, person1@example.com)",
            "Executed.",
            "db > ",
        ])

    def test_persistence(self):
        self.run_script([
            "insert 1 user1 person1@example.com",
            ".exit",
        ])
        result = self.run_script([
            "select",
            ".exit",
        ])
        self.assertEqual(result, [
            "db > (1, user1, person1@example.com)",
            "Executed.",
            "db > ",
        ])

    def test_table_full(self):
        commands = [f"insert {i} user{i} person{i}@example.com" for i in range(1, 1402)]
        commands.append(".exit")
        result = self.run_script(commands)
        self.assertIn("db > Executed.", result[-2:])
        self.assertIn("db > ", result[-2:])

    def test_max_string_length(self):
        long_username = "a" * 32
        long_email = "a" * 255
        result = self.run_script([
            f"insert 1 {long_username} {long_email}",
            "select",
            ".exit",
        ])
        self.assertIn(f"db > (1, {long_username}, {long_email})", result)

    def test_error_long_strings(self):
        long_username = "a" * 33
        long_email = "a" * 256
        result = self.run_script([
            f"insert 1 {long_username} {long_email}",
            "select",
            ".exit",
        ])
        self.assertIn("db > String is too long.", result)

    def test_negative_id_error(self):
        result = self.run_script([
            "insert -1 cstack foo@bar.com",
            "select",
            ".exit",
        ])
        self.assertIn("db > ID must be positive.", result)

    def test_duplicate_id_error(self):
        result = self.run_script([
            "insert 1 user1 person1@example.com",
            "insert 1 user1 person1@example.com",
            "select",
            ".exit",
        ])
        self.assertIn("db > Error: Duplicate key.", result)

    # More tests can be added here for btree, constants, multi-level tree etc.

if __name__ == '__main__':
    unittest.main()
