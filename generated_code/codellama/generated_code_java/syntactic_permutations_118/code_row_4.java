import java.io.FileWriter;
import java.util.Random;

public class Code{
     public static void main(String[] args) throws Exception{
            Random rand = new Random();
			float f1 = rand.nextFloat()*100;
			float f2 = rand.nextFloat()*100;
			float f3 = rand.nextFloat()*100;

			FileWriter file = new FileWriter("file.txt");
			String str = String.valueOf(f1)+ String.valueOf(f2) + String.valueOf(f3);
			file.write(str);
			file.flush();
            file.close();
     }
}