package com.github.javaparser.jrt;
import java.util.Random; //import Random class
import java.io.FileWriter; //import FileWriter class
public class RandomFloats {
    public static void main(String[] args) throws Exception { //main method
        float x = new Random().nextFloat(); //create random float between 0 (inclusive) and 1 (exclusive)
        float y = new Random().nextFloat();
        float z = new Random().nextFloat();
        String s = Float.toString(x) + Float.toString(y) + Float.toString(z); //convert floats to string
        FileWriter fw = new FileWriter("random_floats.txt"); //create filewriter object
        fw.write(s); //write string to file
        fw.close(); //close writer
    }
}