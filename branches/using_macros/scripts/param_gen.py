import sys

class Generator:
    
    def __init__(self, pathIn, pathOut, _nrParams):
	self.fileIn= open(pathIn, 'r')
	self.fileOut= open(pathOut, 'w')
	self.nrParams= int(_nrParams)

	self.conteudo = self.fileIn.readlines()

	for line in self.conteudo:
	    self.generateLine(line)

	self.fileIn.close()
	self.fileOut.close()

    def generateLine(self, line):
	if (line.startswith('template')):
	    self.fileOut.write('template <class ReturnType')
	    for i in range(self.nrParams):
	        self.fileOut.write(', class Param')    
		self.fileOut.write(str(i+1))
  
	    self.fileOut.write('>\n')    
	else:
	    self.fileOut.write(line)
	    

if __name__ == '__main__':
    if len(sys.argv) != 4:
	print 'Usage: param_gen CAMINHO_IN CAMINHO_OUT NR_PARAMS'
    else:
	nameIn = sys.argv[1]
	nameOut = sys.argv[2]
	nrParams = sys.argv[3]
	Generator(nameIn, nameOut, nrParams )
