import java.io.FileWriter;
import java.util.Random;

public class RandomFloat {
    public static void main(String[] args) throws Exception {
        try (FileWriter writer = new FileWriter("random_floats.txt")) {
            String concatString = "";
            for (int i = 0; i < 3; i++) {
                Random random = new Random();
                float randomFloat = random.nextFloat() * 100;
                writer.write(randomFloat + "\n");
                concatString += String.valueOf(randomFloat);
            }
            System.out.println("Concatenated string: " + concatString);
        }
    }
}