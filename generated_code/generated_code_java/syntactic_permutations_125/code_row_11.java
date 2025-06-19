package com.bob;

    import java.io.*;

    public class Code {
        public static void main(String[] args) throws IOException {
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            String input = br.readLine();
            System.out.println(input.trim());
        }
    }