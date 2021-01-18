//
// Created by nickmint on 1/15/21.
//

#ifndef TEMPLATE_STACK_LIGHT_HPP
#define TEMPLATE_STACK_LIGHT_HPP

template <typename T>
class stack_light
{
 public:
  stack_light();
  stack_light(const stack_light& s) = delete;
  stack_light(stack_light&& s) noexcept;
  void operator=(const stack_light& s) = delete;
  void operator=(stack_light&& s) noexcept;
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
        : body(std::move(elem))
    {}
  } *element;
};

template <typename T>
stack_light<T>::stack_light()
    : element(nullptr)
{}

template <typename T>
stack_light<T>::stack_light(stack_light&& s) noexcept
    : element(std::move(s.element))
{
  s.element = nullptr;
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
  tmp_pointer->previous = element;
  element = tmp_pointer;
}

template <typename T>
void stack_light<T>::pop() {
  if (element) {
    node* tmp_pointer = element->previous;
    delete element;
    element = tmp_pointer;
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

template <typename T>
void stack_light<T>::operator=(stack_light&& s) noexcept{
  element = std::move(s.element);
  s.element = nullptr;
}

#endif  // TEMPLATE_STACK_LIGHT_HPP
