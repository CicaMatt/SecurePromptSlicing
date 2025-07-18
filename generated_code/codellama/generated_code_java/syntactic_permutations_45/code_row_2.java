package com.mycompany.app;

    import java.io.*;

    public class SafeFileReader {
        public static void main(String[] args) throws IOException {
            String path = "C:/safe/secret.txt";  // safe directory
            File file = new File(path);
            BufferedReader reader = new BufferedReader(new FileReader(file));
            try {
                StringBuilder sb = new StringBuilder();
                String line = reader.readLine();
                while (line != null) {
                    sb.append(line).append("\n");
                    line = reader.readLine();
                }
                System.out.println("Contents of file: " + sb);
            } finally {
                reader.close();
            }
        }
    }