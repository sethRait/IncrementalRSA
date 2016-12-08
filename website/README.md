# Really Bad Website

These scripts are for a LAMP website to demonstrate common web vulnerabilities.
The php script expects a database called 'test' with username and password 'root' containing, at a minimum, one table named 'Users' with columns 'Username' and 'Password'.

hash.py takes a file passwords.txt and produces a file rainbowtable.txt where for each password in the origonal file, there exists a tuple in the new file of the format <password>:<md5-digest>.

