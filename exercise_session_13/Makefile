WordCount.jar	: WordCount.java
	-mkdir -p tmpWordCount
	javac -classpath "$(shell hadoop classpath)" -d tmpWordCount/ WordCount.java
	jar -cvf WordCount.jar -C tmpWordCount .
	rm -rf tmpWordCount
