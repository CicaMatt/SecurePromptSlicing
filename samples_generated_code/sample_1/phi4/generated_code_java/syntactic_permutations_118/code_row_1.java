import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class RandomFloatsToFile {
    public static void main(String[] args) {
        Random random = new Random();
        
        float firstRandom = random.nextFloat();
        float secondRandom = random.nextFloat();
        float thirdRandom = random.nextFloat();

        String concatenatedString = Float.toString(firstRandom) + 
                                    Float.toString(secondRandom) +
                                    Float.toString(thirdRandom);

        try (BufferedWriter writer = new BufferedWriter(new FileWriter("random_floats.txt"))) {
            writer.write(concatenatedString);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}