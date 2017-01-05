#ifndef POINT_CPP_
#define POINT_CPP_

#include "Point.hpp"
using namespace scorpion::geometry;

//Variables

//Constructors
template<typename T, size_t dimensions>
Point<T, dimensions>::Point(T* collection[dimensions]) : value(new DimensionPoint<T>[dimensions]){
    //Local Variables
    std::string dimensionName = std::string();
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        switch(i){
        case(0u):
            dimensionName = "x";
            break;
        case(1u):
            dimensionName = "y";
            break;
        case(2u):
            dimensionName = "z";
            break;
        default:
            dimensionName = "";
            break;
        }
        if(collection == nullptr){
            this->value[i] = DimensionPoint<T>((T)0, dimensionName);
        }else if(collection[i] == nullptr){
            this->value[i] = DimensionPoint<T>((T)0, dimensionName);
        }else{
            this->value[i] = DimensionPoint<T>((T)(*collection[i]), dimensionName);
        }
    }
}
template<typename T, size_t dimensions>
Point<T, dimensions>::Point(std::initializer_list<T> c) : value(new DimensionPoint<T>[dimensions]){
    //Local Variables
    std::string dimensionName = std::string();
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        dimensionName = Point<T, dimensions>::getDefaultDimensionName(i);
        //std::cout << "[INFO]: Point Dimension Name: " << dimensionName.c_str() << "\n";//!Debugging
        //std::cout << "[INFO]: Point C Value       : " << (T)(*(c.begin() + i)) << "\n";//!Debugging
        if(i >= c.size()){
            std::cout << "[WARNING]: Point initializer list does not have enof!\n";//!Debugging
            this->value[i] = DimensionPoint<T>((T)0, dimensionName);
            continue;
        }
        this->value[i] = DimensionPoint<T>((T)(*(c.begin() + i)), dimensionName);
        //std::cout << "[INFO]: Point New Value[" << i << "]: " << this->getValue(i) << "\n";
    }
}
template<typename T, size_t dimensions>
Point<T, dimensions>::Point(const Point<T, dimensions>& p) : value(new DimensionPoint<T>[dimensions]){//!COPY OVERLOAD
    //Local Variables
    std::string dimensionName = std::string();
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        dimensionName = Point<T, dimensions>::getDefaultDimensionName(i);
        this->value[i] = DimensionPoint<T>((T)p.getValue(i), dimensionName);
    }
}
template<typename T, size_t dimensions>
Point<T, dimensions>::~Point(){
    //for(size_t i = 0u; i < dimensions; i++)
        //delete this->value[i];
    //!delete this->value;//!?
    delete [] this->value;
}

//Functions
template<typename T, size_t dimensions>
std::string Point<T, dimensions>::getDefaultDimensionName(const size_t dimension_index){
    //Local Variables
    std::string dimensionName = std::string("");
    //Process
    switch(dimension_index){
    case(0u):
        dimensionName = std::string("x");
        break;
    case(1u):
        dimensionName = std::string("y");
        break;
    case(2u):
        dimensionName = std::string("z");
        break;
    case(3u):
        dimensionName = std::string("t");
        break;
    default:
        dimensionName = std::string();
        break;
    }
    //Finish
    return(dimensionName);
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::isWithin(const double distance, const Point<T, dimensions> p) const{
    return(this->isWithin(distance, &p));
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::isWithin(const float distance, const Point<T, dimensions> p) const{
    return(this->isWithin(distance, &p));
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::isWithin(const long double distance, const Point<T, dimensions> p) const{
    return(this->isWithin(distance, &p));
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::isWithin(const double distance, const Point<T, dimensions>* p) const{
    //Validate
    if(p == nullptr)return(false);
    //Local Variables
    double dist = this->getDistance(p);
    if(dist < (double)0.0d)return(false);
    //Finish
    return(dist <= distance);
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::isWithin(const float distance, const Point<T, dimensions>* p) const{
    //Validate
    if(p == nullptr)return(false);
    //Local Variables
    float dist = this->getDistanceF(p);
    if(dist < (float)0.0f)return(false);
    //Finish
    return(dist <= distance);
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::isWithin(const long double distance, const Point<T, dimensions>* p) const{
    //Validate
    if(p == nullptr)return(false);
    //Local Variables
    long double dist = this->getDistanceL(p);
    if(dist < (long double)0.0)return(false);
    //Finish
    return(dist <= distance);
}
template<typename T, size_t dimensions>
size_t Point<T, dimensions>::getDimensions(){
    return(dimensions);
}
template<typename T, size_t dimensions>
double Point<T, dimensions>::getDistance(const Point<T, dimensions> p) const{
    return((double)this->getDistance(&p));
}
template<typename T, size_t dimensions>
float Point<T, dimensions>::getDistanceF(const Point<T, dimensions> p) const{
    return((float)this->getDistanceF(&p));
}
template<typename T, size_t dimensions>
long double Point<T, dimensions>::getDistanceL(const Point<T, dimensions> p) const{
    return((long double)this->getDistanceL(&p));
}
template<typename T, size_t dimensions>
double Point<T, dimensions>::getDistance(const Point<T, dimensions>* p) const{
    //Validate
    if(p == nullptr)return((double)-1.0d);
    //Local Variables
    double rdv = (double)0.0d;
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)break;
        //if(this->value[i] == nullptr)continue;
        rdv += pow((this->value[i].value - p->getValue(i)), 2.0d);
    }
    //Finish
    if(rdv < (double)0.0d)return((double)-1.0d);
    return((double)sqrt(rdv));
}
template<typename T, size_t dimensions>
float Point<T, dimensions>::getDistanceF(const Point<T, dimensions>* p) const{
    //Validate
    if(p == nullptr)return((float)-1.0f);
    //Local Variables
    float rdv = (float)0.0f;
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)break;
        //if(this->value[i] == nullptr)continue;
        rdv += powf((this->value[i].value - p->getValue(i)), 2.0f);
    }
    //Finish
    if(rdv < (float)0.0f)return((float)-1.0f);
    return((float)sqrtf(rdv));
}
template<typename T, size_t dimensions>
long double Point<T, dimensions>::getDistanceL(const Point<T, dimensions>* p) const{
    //Validate
    if(p == nullptr)return((long double)-1.0);
    //Local Variables
    long double rdv = (long double)0.0;
    //Process
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)break;
        //if(this->value[i] == nullptr)continue;
        rdv += powl((this->value[i].value - p->getValue(i)), 2.0);
    }
    //Finish
    if(rdv < (long double)0.0)return((long double)-1.0);
    return((long double)sqrtl(rdv));
}
template<typename T, size_t dimensions>
DimensionPoint<T>* Point<T, dimensions>::getDimension(const size_t dimension_index_) const{
    //Validate
    //std::cout << "[INFO]: Point is getting a dimension[" << dimension_index_ << "] pointer!\n";//!Debugging
    if(dimension_index_ >= dimensions){
        std::cerr << "[ERROR]: Point Dimension index is out of range!\n";//!Debugging
        std::cout << "[ERROR]: Point Dimension index is out of range!\n";//!Debugging
        return(nullptr);
    }
    if(this->value == nullptr){
        std::cerr << "[ERROR]: Point Value array is undefined!\n";//!Debugging
        std::cout << "[ERROR]: Point Value array is undefined!\n";//!Debugging
        return(nullptr);
    }
    //if(this->value[dimension_index_] == nullptr)return(nullptr);//Pointless
    //Finish
    //std::cout << "[INFO]: Got a dimension[" << dimension_index_ << "] pointer of: " << this->value[dimension_index_] << "!\n";//!Debugging
    return(const_cast<DimensionPoint<T>* >(&(this->value[dimension_index_])));
}
template<typename T, size_t dimensions>
DimensionPoint<T>* Point<T, dimensions>::getDimension(const std::string dimension_name_) const{
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)break;
        //if(this->value[i] == nullptr)continue;
        if(this->value[i].getName() == dimension_name_)return(const_cast<DimensionPoint<T>* >(&(this->value[i])));
    }
    return(nullptr);
}
template<typename T, size_t dimensions>
T Point<T, dimensions>::getValue(const DimensionPoint<T>* dimension_) const{
    //Validate
    //std::cout << "[INFO]: Point getting value from dimension pointer @ " << (dimension_) << "\n";//!Debugging
    if(dimension_ == nullptr){
        std::cerr << "[ERROR]: Point getValue failed! Undefined dimension!\n";//!Debugging
        return((T)0);
    }
    //Finish
    //std::cout << "[INFO]: Got dimensional value: " << (T)dimension_->value << "from: " << (dimension_) << "\n";//!Debugging
    return((T)dimension_->value);
}
template<typename T, size_t dimensions>
T Point<T, dimensions>::getValue(const size_t dimension_index_) const{
    //std::cout << "[INFO]: Point is getting value by dimension index[" << dimension_index_ << "]!\n";//!Debugging
    return((T)this->getValue(this->getDimension(dimension_index_)));
}
template<typename T, size_t dimensions>
T Point<T, dimensions>::getValue(const std::string dimension_name_) const{
    return((T)this->getValue(this->getDimension(dimension_name_)));
}
template<typename T, size_t dimensions>
std::string Point<T, dimensions>::getDimensionName(const DimensionPoint<T>* dimension_) const{
    //Validate
    if(dimension_ == nullptr)return(std::string());
    //Finish
    return(dimension_->getName());
}
template<typename T, size_t dimensions>
std::string Point<T, dimensions>::getDimensionName(const size_t dimension_index_) const{
    //Local Variables
    DimensionPoint<T>* dim = nullptr;
    //Process
    dim = this->getDimension(dimension_index_);
    if(dim == nullptr)return(std::string());
    //Finish
    return(this->getDimensionName(dim));
}

//Methods
template<typename T, size_t dimensions>
void Point<T, dimensions>::setValue(DimensionPoint<T>* dim, const T v){
    //Process
    if(dim == nullptr)return;
    //Finish
    //std::cout << "[INFO]: Point is Setting Dimension @ " << dim << " from: " << dim->value << " to: " << v << "\n";//!Debugging
    dim->value = v;
    //std::cout << "[INFO]:  Point has set Dimension   @ " << dim << " to: " << dim->value << "\n";
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::setValue(const size_t dimension_index_, const T v){
    //Local Variables
    DimensionPoint<T>* dim = nullptr;
    //Process
    //std::cout << "[INFO]: Point setting dimension[" << dimension_index_ << "] to: " << v << "\n";//!Debugging
    dim = this->getDimension(dimension_index_);
    if(dim == nullptr){
        std::cerr << "[ERROR]: Point setValue Failed to getDimension!\n";//!Debugging
        return;
    }
    this->setValue(dim, v);
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::setValue(const std::string dimension_name_, const T v){
    //Local Variables
    DimensionPoint<T>* dim = nullptr;
    //Process
    dim = this->getDimension(dimension_name_);
    if(dim == nullptr){
        std::cerr << "[ERROR]: Point setValue name Failed to getDimension!\n";//!Debugging
        return;
    }
    this->setValue(dim, v);
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::setDimensionName(DimensionPoint<T>* dim, const std::string str){
    //Process
    if(dim == nullptr)return;
    dim->setName(str);
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::setDimensionName(const size_t dimension_index_, const std::string str){
    //Local Variables
    DimensionPoint<T>* dim = nullptr;
    //Process
    dim = this->getDimension(dimension_index_);
    if(dim == nullptr)return;
    this->setDimensionName(dim, str);
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::setDimensionName(const std::string dimension_name_, const std::string str){
    //Local Variables
    DimensionPoint<T>* dim = nullptr;
    //Process
    dim = this->getDimension(dimension_name_);
    if(dim == nullptr)return;
    this->setDimensionName(dim, str);
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::debug(std::ostream* os_) const{
    if(os_ == nullptr)os_ = (std::ostream*)(&std::cout);
    (*os_) << "[INFO]: Debugging Point @ " << (this) << "\n";
    (*os_) << "[INFO]: Debugging Point Dimension(s)[" << this->getDimensions() << "]:\n";
    for(size_t i = 0u; i < dimensions; i++){
        (*os_) << "[INFO]: Debugging Point Dimension[" << i << "]:\n";
        this->value[i].debug(os_);
        (*os_) << "\n";
    }
    (*os_) << "[INFO]: Finished Debugging Point @ " << (this) << "\n";
}

//Operator
template<typename T, size_t dimensions>
bool Point<T, dimensions>::operator != (const Point<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)return(true);
        //if(this->value[i] == nullptr)return(true);
        if(p.getDimension(i) == nullptr)return(true);
        if((this->value[i]) != (*p.getDimension(i)))return(true);
    }
    return(false);
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::operator == (const Point<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)return(false);
        //if(this->value[i] == nullptr)return(false);
        if(p.getDimension(i) == nullptr)return(false);
        if((this->value[i]) != (*p.getDimension(i)))return(false);
    }
    return(true);
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::operator <= (const Point<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)return(false);
        //if(this->value[i] == nullptr)return(false);
        if(p.getDimension(i) == nullptr)return(false);
        if((this->value[i]) > (*p.getDimension(i)))return(false);
    }
    return(true);
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::operator >= (const Point<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)return(false);
        //if(this->value[i] == nullptr)return(false);
        if(p.getDimension(i) == nullptr)return(false);
        if((this->value[i]) < (*p.getDimension(i)))return(false);
    }
    return(true);
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::operator < (const Point<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)return(false);
        //if(this->value[i] == nullptr)return(false);
        if(p.getDimension(i) == nullptr)return(false);
        if((this->value[i]) >= (*p.getDimension(i)))return(false);
    }
    return(true);
}
template<typename T, size_t dimensions>
bool Point<T, dimensions>::operator > (const Point<T, dimensions> &p)const{
    for(size_t i = 0u; i < dimensions; i++){
        if(this->value == nullptr)return(false);
        //if(this->value[i] == nullptr)return(false);
        if(p.getDimension(i) == nullptr)return(false);
        if((this->value[i]) <= (*p.getDimension(i)))return(false);
    }
    return(true);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Point<T, dimensions>::operator + (const Point<T, dimensions> &p)const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, (this->getValue(i) + p.getValue(i)));
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Point<T, dimensions>::operator - (const Point<T, dimensions> &p)const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++){
        //std::cout << "[INFO]: Subtracting Point[" << i << "]: " << this->getValue(i) << " - " << p.getValue(i) << " = " << (this->getValue(i) - p.getValue(i)) << "\n";//!Debugging
        rpv.setValue(i, (this->getValue(i) - p.getValue(i)));
    }
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Point<T, dimensions>::operator * (const Point<T, dimensions> &p)const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, (this->getValue(i) * p.getValue(i)));
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Point<T, dimensions>::operator / (const Point<T, dimensions> &p)const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++){
        if(p.getValue(i) == static_cast<T>(0)){
            std::cerr << "[ERROR]: Point Encountered a Divide-by-Zero Error!\n";//!Fail silently?
            rpv.setValue(i, (this->getValue(i)));
            continue;
        }
        rpv.setValue(i, (this->getValue(i) / p.getValue(i)));
    }
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Point<T, dimensions>::operator + (const T &value)const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, this->getValue(i) + value);
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Point<T, dimensions>::operator - (const T &value)const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, this->getValue(i) - value);
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Point<T, dimensions>::operator * (const T &value)const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, this->getValue(i) * value);
    return(rpv);
}
template<typename T, size_t dimensions>
Point<T, dimensions> Point<T, dimensions>::operator / (const T &value)const{
    Point<T, dimensions> rpv = Point<T, dimensions>();
    T v = value;
    if(value == static_cast<T>(0)){
        std::cerr << "[ERROR]: Point::/ Encountered a Divide-by-Zero Error!\n";//!Fail Silently?
        v = static_cast<T>(1);
    }
    for(size_t i = 0u; i < dimensions; i++)
        rpv.setValue(i, this->getValue(i) / v);
    return(rpv);
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::operator += (const Point<T, dimensions> &p){
    for(size_t i = 0u; i < dimensions; i++)
        this->setValue(i, (this->getValue(i) + p.getValue(i)));
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::operator -= (const Point<T, dimensions> &p){
    for(size_t i = 0u; i < dimensions; i++){
        std::cout << "[INFO]: Subtracting/Setting Point[" << i << "]: " << this->getValue(i) << " - " << p.getValue(i) << " = " << (this->getValue(i) - p.getValue(i)) << "\n";//!Debugging
        this->setValue(i, static_cast<T>(this->getValue(i) - p.getValue(i)));
    }
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::operator *= (const Point<T, dimensions> &p){
    for(size_t i = 0u; i < dimensions; i++)
        this->setValue(i, (this->getValue(i) * p.getValue(i)));
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::operator /= (const Point<T, dimensions> &p){
    for(size_t i = 0u; i < dimensions; i++)
        this->setValue(i, (this->getValue(i) / p.getValue(i)));
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::operator += (const T &value){
    for(size_t i = 0u; i < dimensions; i++)
        this->setValue(i, (this->getValue(i) + value));
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::operator -= (const T &value){
    for(size_t i = 0u; i < dimensions; i++)
        this->setValue(i, (this->getValue(i) - value));
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::operator *= (const T &value){
    for(size_t i = 0u; i < dimensions; i++)
        this->setValue(i, (this->getValue(i) * value));
}
template<typename T, size_t dimensions>
void Point<T, dimensions>::operator /= (const T &value){
    if(value == static_cast<T>(0)){
        std::cerr << "[ERROR]: Point encountered a Divide-by-Zero!\n";//!Debugging
        return;
    }
    for(size_t i = 0u; i < dimensions; i++)
        this->setValue(i, (this->getValue(i) / value));
}
template<typename T, size_t dimensions>
Point<T, dimensions>& Point<T, dimensions>::operator = (const Point<T, dimensions> &p){//!ASSIGNMENT OVERLOAD
    //!Used for deep copies see also COPY OVERLOAD
    //Validate
    if(this == &p)return(*this);
    //Local Variables
    //Process
    //std::cout << "[INFO]: Point conducting deep copies...\n";//!Debugging
    delete [] this->value;
    this->value = new DimensionPoint<T>[dimensions];
    for(size_t i = 0u; i < dimensions; i++)
        this->value[i] = DimensionPoint<T>((T)p.getValue(i), p.getDimensionName(i));
    //Finish
    return(*this);
}

#endif // POINT_CPP_
