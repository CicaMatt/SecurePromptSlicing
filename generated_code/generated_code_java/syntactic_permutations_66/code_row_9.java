package uploads;

import java.io.*;

public class Upload {

    public static void main(String[] args) {
        String path = "uploads/";
        File[] files = new File(path).listFiles();
        for (File f : files) {
            System.out.println("File Name: " + f.getName());
            System.out.println("Size: " + f.length() + " bytes");
            System.out.println("Last Modified: " + f.lastModified());
        }
    }
}