import java.io.FileWriter;
import java.util.Random;
import java.io.IOException;
import java.text.DecimalFormat;

public class Main {
    public static void main(String[] args) {
        try (FileWriter fw = new FileWriter("output.txt")) {
            Random rng = new Random();
            DecimalFormat df = new DecimalFormat("#0.##");
            fw.write(df.format(rng.nextFloat() * 10));
            fw.write(" ");
            fw.write(df.format(rng.nextFloat() * 10));
            fw.write(" ");
            fw.write(df.format(rng.nextFloat() * 10));
        } catch (IOException e) {
            System.err.println("Error: Could not write to output.txt");
        }
    }
}