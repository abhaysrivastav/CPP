# C_plus_plus

### Partial Template Specialization

***A General Template***

```
template <class Window, class Controller>
class Widget
{
   ... generic implementation ...
};
```

***Total Template Specialization***
```
template <>
class Widget<ModalDialog, MyController>
{
   ... specialized implementation ...
};
```
***Partial Template Specialization***

```
template<class Window>
class Widget<Window, MyController>
{
  ...Partial Template Specialization...
}
```
