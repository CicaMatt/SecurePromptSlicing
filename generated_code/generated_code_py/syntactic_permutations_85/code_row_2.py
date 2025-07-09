def temperature_for_location(date,latitude,longitude):
    connect("localhost",27017)
    db=database_name
    col=collection_name
    myquery={"Date":date,"Latitude":latitude,"Longitude":longitude}
    projection={"Temperature":1, "_id": 0}
    result=col.find(myquery,projection)
    return list(result)