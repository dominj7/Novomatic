
template<class T, class UnaryPredicate>
void cutString(T *text, UnaryPredicate pred) {
    std::reverse(text->begin(), text->end());
    text->erase(text->begin(), std::find_if_not(text->begin(), text->end(), pred));
    std::reverse(text->begin(), text->end());
    text->erase(text->begin(), std::find_if_not(text->begin(), text->end(), pred));
}
