#include <fstream>
#include <string>
#include <vector>

int main(int argc, char **argv) {
   auto loader = [](char *file) {
       std::vector<std::string> vector;
       std::ifstream stream{file};
       std::string line;
       while (std::getline(stream, line)) {
           vector.emplace_back(std::move(line));
       }
       return std::move(vector);
   };
   auto words_1 = loader(argv[1]);
   auto words_2 = loader(argv[2]);

   std::vector<size_t> positive_indices;

   for (auto const &word_2 : words_2)
   {
       size_t word_one_index{0};
       for (auto const &word_1 : words_1)
       {
           if (word_1 == word_2) {
               positive_indices.emplace_back(word_one_index);
               break;
           }
           word_one_index++;
       }
   }

   std::ofstream stream{"output"};
   for (auto index : positive_indices)
       stream << words_1[index] << std::endl;

   return 0;
}
