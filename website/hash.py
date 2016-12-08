import md5
import json
l = open('passwords.txt').read().splitlines()
d = {}
f = open("rainbowtable.txt","w")
for password in l:
	#d[password] = md5.new(password).hexdigest()
	f.write("{}:{}\n".format(password, md5.new(password).hexdigest()))
#f = open("rainbowtbale.json", 'w')
#json.dump(d,f)
f.close()
