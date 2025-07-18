package com.dummy;

import java.io.*;

public class CheckSum {
    public static void main(String[] args) throws Exception {
        String contents = readFile("file1.txt");
        int checksum = calculateChecksum(contents);
        writeFile("file2.txt", checksum + " " + (checksum == 0 ? "empty" : "not empty"));
    }

    public static String readFile(String fileName) throws Exception {
        BufferedReader reader = new BufferedReader(new FileReader(fileName));
        try {
            StringBuilder sb = new StringBuilder();
            String line = null;
            while ((line = reader.readLine()) != null) {
                sb.append(line + System.getProperty("line.separator"));
            }
            return sb.toString();
        } finally {
            reader.close();
        }
    }

    public static int calculateChecksum(String contents) throws Exception {
        if (contents == null || "".equals(contents)) {
            throw new IllegalArgumentException("Contents cannot be empty");
        }
        byte[] bytes = contents.getBytes();
        int checksum = 0;
        for (byte b : bytes) {
            checksum += b;
        }
        return checksum;
    }

    public static void writeFile(String fileName, String contents) throws Exception {
        BufferedWriter writer = new BufferedWriter(new FileWriter(fileName));
        try {
            writer.write(contents);
        } finally {
            writer.close();
        }
    }
}