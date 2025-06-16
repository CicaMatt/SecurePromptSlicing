import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
        FileWriter fw = new FileWriter("myfile.txt", true); 
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write("Hello World");
        bw.close();
    }
}