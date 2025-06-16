import java.util.Random;
import java.io.FileWriter;

public class RandomFloats {
    public static void main(String[] args) {
        try {
            FileWriter fw = new FileWriter("floats.txt");
            Random rand = new Random();
            float a = rand.nextFloat() * 10;
            float b = rand.nextFloat() * 20;
            float c = rand.nextFloat() * 30;
            String s = Float.toString(a) + " " +
                Float.toString(b) + " " +
                Float.toString(c);
            fw.write(s);
            fw.close();
        }
        catch (Exception e){
            System.out.println("Something went wrong");
        }
    }
}