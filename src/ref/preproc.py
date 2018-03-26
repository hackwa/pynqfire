fname = "cpp_FIR.inc"
with open(fname) as f:
	content = f.readlines()
content = [x.strip()[:-1] for x in content]

with open("coeff.txt", 'w') as f:
	for i in range(len(content)):
		f.write("w[%d] = (coef_t) %d;\n"%(i,int(content[i])))
		if (i == len(content)-1):
			f.write("\n")
