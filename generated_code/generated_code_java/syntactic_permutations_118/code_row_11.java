package com.company;

import java.io.*;
import java.util.Random;

public class Main {

    public static void main(String[] args) throws IOException {
        Random rand = new Random();

        float num1 = rand.nextFloat();
        float num2 = rand.nextFloat();
        float num3 = rand.nextFloat();

        String strNum1 = Float.toString(num1);
        String strNum2 = Float.toString(num2);
        String strNum3 = Float.toString(num3);

        FileWriter fileWriter = new FileWriter("random_floats.txt");
        PrintWriter printWriter = new PrintWriter(fileWriter);

        printWriter.println(strNum1);
        printWriter.println(strNum2);
        printWriter.println(strNum3);

        printWriter.close();
    }
}