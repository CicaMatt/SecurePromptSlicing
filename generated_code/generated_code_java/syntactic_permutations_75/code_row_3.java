import java.util.*;
public class Person {
	int age;
	String name;
}

public static Person * allocate() {
    return new Person();
}