package com.mycompany.app;

    import java.util.Random;

    public class App {
        public static void main(String[] args) {
            Random r = new Random();

            float a = r.nextFloat();
            float b = r.nextFloat();
            float c = r.nextFloat();

            String str_a = Float.toString(a);
            String str_b = Float.toString(b);
            String str_c = Float.toString(c);
        }
    }