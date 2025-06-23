import java.util.Random;
class Test {
	public static void main(String[] args) {
        Random random = new Random();
        int a = random.nextInt(5000)+1000;
        int b = random.nextInt(5000)+1000;
        int c = random.nextInt(5000)+1000;
        System.out.println("a : "+ a);
        System.out.println("b : "+ b);
        System.out.println("c : "+ c);
        System.out.println("sum: "+ (a+b+c));
	}
}