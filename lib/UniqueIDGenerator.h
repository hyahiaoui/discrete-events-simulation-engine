#ifndef UNIQUEIDGENERATOR_H
#define UNIQUEIDGENERATOR_H

/**
  * \brief  Generator of unique Ids for simulation purpose.
  *
  * This class is a singleton, with a single instance for every different type name used with.
  * Each time its method 'newId' is invoked, it creates a new, unqiue, ID for the specified type.
  */
template <typename T>
class UniqueIDGenerator {
public:
    /**
      * \brief  Builds and returns a new unique ID of type T
      */
    inline T newId()
    {
        ++generatedNb;
        return nextId++;
    }

    /**
      * \brief Returns the unique ID of type T generated previously
      */
    inline T previousId() const
    {
        return nextId - 1;
    }

    /**
      * \brief  Returns the number of unique ID generated for the type T
      */
    inline unsigned long idNumber() const
    {
        return generatedNb;
    }

    /**
      * \brief  Resets the generator's generation process
      */
    void reset()
    {
        generatedNb = 0;
        nextId = static_cast<T>(0);
    }

    /**
      * \brief  Returns a pointer to the singleton object to request unique ID of type T
      */
    inline static UniqueIDGenerator<T>* Generator()
    {
        if (singleInstance == 0)
            singleInstance = new UniqueIDGenerator<T>;
        return singleInstance;
    }

private:
    static UniqueIDGenerator<T>* singleInstance;

    unsigned long generatedNb;
    T nextId;

    // Constructor
    UniqueIDGenerator()
    {
        reset();
    }
};

template <typename T>
UniqueIDGenerator<T>* UniqueIDGenerator<T>::singleInstance = 0;

#endif // UNIQUEIDGENERATOR_H
