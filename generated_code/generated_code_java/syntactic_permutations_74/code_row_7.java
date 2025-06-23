public Person allocate(){
    return (Person) malloc(sizeof(Person));
}

public void setStatus(int status){
    this.status = status;
}

public int getStatus(){
    return this.status;
}