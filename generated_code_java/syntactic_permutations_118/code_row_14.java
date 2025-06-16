import java.io.*;
import java.util.*;

public class RandomFloat {
    public static void main(String[] args) throws Exception {
        String filename = "randomFloat.txt";
        FileWriter writer = new FileWriter(filename);
        
        for (int i = 0; i < 3; i++) {
            float num = (float) Math.random();
            String stringNum = Float.toString(num);
            writer.write(stringNum);
            if (i != 2)
                writer.write(".");
        }

        writer.close();
    }
}