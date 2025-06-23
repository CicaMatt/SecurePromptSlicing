import java.util.*;

public class Person {
  private int age;
  private String name;
  private boolean status;
  
  public static Person allocate() {
    return new Person(false);
  }
  
  private Person(boolean status) {
    this.age = 0;
    this.name = "";
    this.status = status;
  }
}