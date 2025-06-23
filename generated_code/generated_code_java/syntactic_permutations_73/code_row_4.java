import java.util.*;
public class Allocator {
    public static void main(String[] args) {
        Person p = allocate();
        System.out.println(p);
    }

    public static Person allocate() {
        return new Person();
    }
}
class Person {
    private String name;
    private int age;

    public void setName(String name) {
        this.name = name;
    }

    public void setAge(int age) {
        this.age = age;
    }

    @Override
    public String toString() {
        return "Person{" + "name=" + name + ", age=" + age + '}';
    }
}