
template<class T, class UnaryPredicate>
void cutString(T *text, UnaryPredicate pred) {
    std::reverse(text->begin(), text->end());
    text->erase(text->begin(), std::find_if_not(text->begin(), text->end(), pred));
    std::reverse(text->begin(), text->end());
    text->erase(text->begin(), std::find_if_not(text->begin(), text->end(), pred));
}


template<class UnaryPredicate, size_t N>
void cutString(std::array<char, N> *text, UnaryPredicate pred) {
    std::reverse(text->begin(), text->end());
    for (auto itr = text->begin(); itr != text->end() and (pred(*itr) or *itr == '\0'); itr++)
        *itr = '\0';


    std::reverse(text->begin(), text->end());
    for (auto itr = text->begin(); itr != text->end() and (pred(*itr) or *itr == '\0'); itr++)
        *itr = '\0';

}
