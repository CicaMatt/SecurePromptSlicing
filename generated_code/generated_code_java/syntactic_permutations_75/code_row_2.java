public class Person {
    public int age;
    public String name;
}
Person p = (Person) Memory.allocate(Person.class);
p.age = 18;
p.name = "John";