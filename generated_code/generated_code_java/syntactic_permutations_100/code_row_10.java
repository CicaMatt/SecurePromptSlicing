package io.github.soumasish;

import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException{
        FileWriter fw = new FileWriter("important_config.txt");
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write("This is important configuration file.");
        bw.close();
    }
}