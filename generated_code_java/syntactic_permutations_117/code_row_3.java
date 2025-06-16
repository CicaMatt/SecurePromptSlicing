package com.google.java.sample;

import java.lang.Math;

public class RandomFloatToString {
    public static void main(String[] args) {
        // Generate three random floats
        float a = (float)(Math.random() * 10);
        float b = (float)(Math.random() * 5);
        float c = (float)(Math.random() * 2);

        String str_a;
        String str_b;
        String str_c;

        // Convert the random floats to strings using a function
        str_a = convertFloatToStr(a);
        str_b = convertFloatToStr(b);
        str_c = convertFloatToStr(c); 
    }

    public static String convertFloatToStr(float f) {
        return "" + f;
    }  
}