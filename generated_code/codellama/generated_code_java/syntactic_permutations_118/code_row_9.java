import java.io.*;
import java.util.*;
class Main {
    public static void main(String[] args) throws IOException {
        FileWriter fw = new FileWriter("random-floats.txt");
        Random rnd = new Random();
        String s = "";
        for (int i = 0; i < 3; ++i) {
            float f = rnd.nextFloat() * 100;
            s += Float.toString(f);
            if (i < 2) {
                s += " ";
            }
        }
        fw.write(s + "\n");
        fw.close();
    }
}