public class Person {

	private int id;
    private String name;
    private int age;
    
    public Person(int id, String name, int age) {
        this.id = id;
        this.name = name;
        this.age = age;
    }

	public static void main(String[] args) {

		Person person = new Person(123456789, "John Doe", 30);
	}
}