package io.jenkins.java; 
import java.io.FileInputStream;
import java.util.*;

public class App {
	
    public static void main(String[] args) throws Exception {
        FileInputStream fis = new FileInputStream("/safe/input_file.txt");
        Scanner scanner = new Scanner(fis);
        while (scanner.hasNext()) {
            System.out.println(scanner.nextLine());
        }
    }	
}