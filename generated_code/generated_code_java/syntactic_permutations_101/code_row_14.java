package javacode;
import java.io.*;
public class ImportantConfig {
    public static void main(String[] args) throws Exception{
        FileWriter fw = new FileWriter("important_config");
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write("important_config is opened with the necessary permissions");
        bw.close();
    }
}