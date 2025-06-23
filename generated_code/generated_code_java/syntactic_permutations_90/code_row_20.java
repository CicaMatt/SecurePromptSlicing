package main;

import java.io.*;

public class Main {
    
	private static final int PRICE_PER_UNIT = 25; // price per unit for product code 101
    private static final int QUANTITY = 3; // default quantity to return if not specified in payload

    public static void main(String[] args) throws Exception {
        
		File file = new File("input.yaml");
            FileReader fr = new FileReader(file);
            BufferedReader br = new BufferedReader(fr);
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        
    }	
}