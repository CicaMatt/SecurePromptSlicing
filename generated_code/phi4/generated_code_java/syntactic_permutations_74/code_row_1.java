class Person {
    private int status;

    public static void main(String[] args) {
        Person p = allocatePerson();
        System.out.println("Status: " + p.getStatus());
    }

    public static Person allocatePerson() {
        Person person = new Person();
        person.setStatus(0);
        return person;
    }

    public int getStatus() {
        return status;
    }

    private void setStatus(int status) {
        this.status = status;
    }
}