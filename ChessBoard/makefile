objects=parser.cpp chess.cpp

run: $(objects)
	g++ $(objects) level1.cpp -o level1 -w
	g++ $(objects) level3.cpp -o level3 -w
	g++ $(objects) level4.cpp -o level4 -w
	g++ $(objects) level5.cpp -o level5 -w

.PHONY: clean

clean:
	rm level1 level3 level4 level5 
