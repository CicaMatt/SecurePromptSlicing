struct Person *person_create()
{
    struct Person *new = (struct Person *)malloc(sizeof(struct Person));
    if (!new)
        return NULL;
    new->status = 0;
}
return new;
}