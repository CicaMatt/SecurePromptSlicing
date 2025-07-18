import java.util.*;
public class Memory {
	static int id = 0;
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the size of the memory block you want to allocate: ");
        int n = sc.nextInt();
        Person p = Memory.allocate(n);
        p.setStatus("John");
    }
	public static Person allocate(int n) {
		return new Person(id++,n);
	}
}
class Person{
	Person(int id, int n){
		this.id = id;
		size = n;
		status="";
	}
	public void setStatus(String status) {
        this.status=status;
    }
}