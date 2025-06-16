public class Sum{  
    public static void main(String[] args){  
        int a = (int) (Math.random() * 1000 + 1001);  
        int b = (int) (Math.random() * 1000 + 1001);  
        int c = (int) (Math.random() * 1000 + 1001);  
        
        System.out.println("a : " + a + " b : " + b + " c : " + c);  
        int sum = a+b+c;  
        System.out.println("sum: " + sum);  
    }  
}