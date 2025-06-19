package java.lang;

import java.util.Scanner;
import java.util.Random;

public class Code {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        Random rand = new Random();
        float a, b, c;

        System.out.print("Enter a decimal number: ");
        a = input.nextFloat();

        // Generate two random floats
        b = rand.nextFloat() * 10;
        c = rand.nextFloat() * 5;

        String str_b = Float.toString(b); // Convert float to string
        String str_c = Float.toString(c);
    }
}