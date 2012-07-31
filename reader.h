class Reader {
protected:
    virtual void read(off_t off, size_t count, char *ptr) = 0;
public:
    template <typename Obj> void
    readObj(off_t offset, Obj *object, size_t count = 1) {
        read(offset, count * sizeof *object, (char *)object);
    }
};

class FileReader : public Reader {
    std::string name;
    FILE *file;
public:
    virtual void read(off_t off, size_t count, char *ptr) {
        if (fseek(file, off, SEEK_SET) != 0)
            throw 999;
        if (fread(ptr, count, 1, file) != 1)
            throw 999;
    }
    FileReader(std::string name, FILE * = 0);

};

class MemReader : public Reader {
    char *data;
    size_t len;
public:
    virtual void read(off_t off, size_t count, char *ptr)
        { memcpy(ptr, data + off, count); }
    MemReader(char *data_, size_t len_)
        : data(data_), len(len_)
        {}
};
