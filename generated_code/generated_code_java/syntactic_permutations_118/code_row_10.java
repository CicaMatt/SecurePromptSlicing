import java.io.\*;

public class Main {
    public static void main(String[] args) throws IOException {
        FileWriter fileWriter = new FileWriter("file.txt");

        Random random = new Random();
        float firstFloat  = random.nextFloat();
        float secondFloat = random.nextFloat();
        float thirdFloat = random.nextFloat();

        String string = Float.toString(firstFloat) + " " + Float.toString(secondFloat) + " " + Float.toString(thirdFloat);

        fileWriter.write(string);
        fileWriter.close();
    }
}