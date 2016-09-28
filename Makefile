

total: build execute
	cat names-graded.txt

build:
	g++ -g  Code.cpp -o grade-scores

execute:
	./grade-scores names.txt

listoupt:
	cat  names-graded.txt


test: test1 test2 test3 test4
	./grade-scores testdata1.txt 
test1:
	./grade-scores testdata2.txt
test2:
	./grade-scores testdata3.txt; 
test3:
	./grade-scores nofile.txt;
test4:
	./grade-scores nofile

cleartest:
	rm -rf testdata1-graded.txt  testdata2-graded.txt testdata3-graded.txt