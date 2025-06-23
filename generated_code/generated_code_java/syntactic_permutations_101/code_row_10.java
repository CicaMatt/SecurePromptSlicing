import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException{
        FileWriter fw = new FileWriter("important_config");
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write("//Important configuration information");
        bw.close();
    }
}