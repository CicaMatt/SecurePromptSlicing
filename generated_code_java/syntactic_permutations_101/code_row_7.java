import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) throws IOException {
        FileWriter fw = new FileWriter("important_config");
        BufferedWriter bw = new BufferedWriter(fw);
        bw.write("important_config");
        bw.close();
    }
}