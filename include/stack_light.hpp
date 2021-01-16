//
// Created by nickmint on 1/15/21.
//

#ifndef TEMPLATE_STACK_LIGHT_HPP
#define TEMPLATE_STACK_LIGHT_HPP

template <typename T>
class stack_light
{
 public:
  explicit stack_light(const T& first_element);
  const T& head() const;
  void push(const T& value);
  void push(T&& value);
  void pop();
  ~stack_light();

 private:
  struct node
  {
    T body;
    node* previous;
    explicit node(const T& elem)
        : body(elem)
    {}
    explicit node(T&& elem)
        : body(std::forward<T>(elem))
    {}
  } *element;
};

template <typename T>
stack_light<T>::stack_light(const T& first_element)
{
  element = new node(first_element);
  //element->body = first_element;
  element->previous = nullptr;
}

template <typename T>
const T& stack_light<T>::head() const {
  if (!element) throw std::runtime_error("No elements in stack");
  return element->body;
}

template <typename T>
void stack_light<T>::push(const T& value) {
  node* tmp_pointer = new node(value);
  //tmp_pointer->body = value;
  tmp_pointer->previous = element;
  element = tmp_pointer;
}

template <typename T>
void stack_light<T>::push(T&& value) {
  node* tmp_pointer = new node(std::move(value));
  //tmp_pointer->body = std::forward<T&&>(value);
  tmp_pointer->previous = element;
  element = tmp_pointer;
}

template <typename T>
void stack_light<T>::pop() {
  if (element->previous) {
    node* tmp_pointer = element->previous;
    delete element;
    element = tmp_pointer;
  } else {
    delete element;
    element = nullptr;
  }
}

template <typename T>
stack_light<T>::~stack_light() {
  if (element){
    while (element->previous){
      node* tmp_pointer = element;
      element = element->previous;
      delete tmp_pointer;
    }
    delete element;
  }
}

#endif  // TEMPLATE_STACK_LIGHT_HPP
