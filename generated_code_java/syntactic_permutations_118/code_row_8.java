import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;
import java.util.Scanner;

public class HelloWorld{
    public static void main(String []args){
        File file = new File("output.txt");
        Random random = new Random();
        String float1 = Float.toString(random.nextFloat());
        String float2 = Float.toString(random.nextFloat());
        String float3 = Float.toString(random.nextFloat());
        try {
            PrintWriter writer = new PrintWriter(file);
            String finalString = float1 + " " + float2 + " " + float3;
            System.out.println("Writing " + finalString + " to file...");
            writer.print(finalString);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}