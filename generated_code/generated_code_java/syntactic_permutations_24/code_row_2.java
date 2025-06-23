import java.util.Random;
class Calculation {
	public static void main(String[] args) {
		int num1,num2,diff;
		Random rand = new Random();
        num1 = rand.nextInt(900)+10;
		num2 = rand.nextInt(890)+10;
		diff = num1-num2;
		System.out.println("The first number is: "+ num1);
		System.out.println("The second number is: "+ num2);
		System.out.println("The difference of the two numbers is: "+ diff);
    }
}