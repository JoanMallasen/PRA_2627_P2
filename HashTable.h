#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>

#include "Dict.h"
#include "TableEntry.h"
#include "../PRA_2627_P1/Practica1/ListLinked.h"

template <typename V>

class HashTable: public Dict<V> {

    private:
        int n;                                  // Núemero de elementos almacenados acutalmente
        int max;                                // Tamaño total de la tabla (Número de cubetas)
        ListLinked<TableEntry<V>>* table;       // Array dinámico de punteros a listas enlazadas
                                                // donde cada cubeta table[i] es unalista de TableEntry<V>

        int h(std::string key) {
            int valor_key = 0;

            for (int i = 0; i < key.length(); i++) {
                valor_key += static_cast<int>(key.at(i));
            }
            
            return valor_key % max;
        }

    public:
        HashTable(int size) {
            table = new ListLinked<TableEntry<V>>[size];
            n = 0;
            max = size;
        }

        ~HashTable() {
            delete[] table;
        }

        int capacity() {
            return max;
        }

        V operator[](std::string key) {
            return search(key);
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
            out << "====================\n";

            for (int i = 0; i < th.max; i++) {
                out << "\n== Cubeta " << i << " ==\n" << th.table[i] << "\n";
            }

            out << "\n====================\n";

            return out;
        }

        void insert(std::string key, V value) {
            int pos = h(key);
            
            if (table[pos].search(TableEntry<V>(key)) != -1) {
                throw std::runtime_error("Key '" + key + "' ya existe!");
            }
            table[pos].prepend(TableEntry<V>(key, value));
            n++;
        }   

        V search (std::string key) {
            int pos = h(key);
            int idx = table[pos].search(TableEntry<V>(key));
            
            if(idx == -1) {
                throw std::runtime_error("Key '" + key + "' no encontrada!");
            }
            return table[pos].get(idx).value;
        }

        V remove (std::string key) {
            int pos = h(key);
            int idx = table[pos].search(TableEntry<V>(key));
            
            if(idx == -1) {
                throw std::runtime_error("Key '" + key + "' no encontrada!");
            }
            TableEntry<V> removed = table[pos].remove(idx);
            n--;
            return removed.value;
        }

        int entries() override {
            return n;
        }
};

#endif