import java.util.Random;
public class Hello {
    public static void main(String[] args) {
        // Declare variables
        float randomNumber1,randomNumber2,randomNumber3;
        String str1,str2,str3,result;
        Random rand = new Random();
        
        // Assign values to the variables
        randomNumber1 = rand.nextFloat() * 100;
        randomNumber2 = rand.nextFloat() * 50; 
        randomNumber3 = rand.nextFloat() * 75;

        str1 = Float.toString(randomNumber1);
        str2 = Float.toString(randomNumber2); 
        str3 = Float.toString(randomNumber3);
        result = str1 +" "+ str2 + " " +str3;
        System.out.println(result);
    }
}