<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>Entry</class>
 <widget class="QDialog" name="Entry">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>314</width>
    <height>443</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>Dialog</string>
  </property>
  <layout class="QVBoxLayout" name="verticalLayout_2">
   <item>
    <layout class="QFormLayout" name="formLayout">
     <property name="fieldGrowthPolicy">
      <enum>QFormLayout::AllNonFixedFieldsGrow</enum>
     </property>
     <item row="1" column="1">
      <widget class="QDateEdit" name="dateEdit_date"/>
     </item>
     <item row="1" column="0">
      <widget class="QLabel" name="label">
       <property name="text">
        <string>Date</string>
       </property>
      </widget>
     </item>
     <item row="2" column="0">
      <widget class="QLabel" name="label_2">
       <property name="text">
        <string>PPM</string>
       </property>
      </widget>
     </item>
     <item row="2" column="1">
      <widget class="QSpinBox" name="spinBox_ppm">
       <property name="maximum">
        <number>3000</number>
       </property>
       <property name="singleStep">
        <number>100</number>
       </property>
      </widget>
     </item>
     <item row="3" column="0">
      <widget class="QLabel" name="label_3">
       <property name="text">
        <string>PH</string>
       </property>
      </widget>
     </item>
     <item row="3" column="1">
      <widget class="QDoubleSpinBox" name="doubleSpinBox_ph">
       <property name="decimals">
        <number>1</number>
       </property>
       <property name="maximum">
        <double>14.000000000000000</double>
       </property>
       <property name="singleStep">
        <double>0.100000000000000</double>
       </property>
       <property name="value">
        <double>6.000000000000000</double>
       </property>
      </widget>
     </item>
     <item row="4" column="0">
      <widget class="QLabel" name="label_4">
       <property name="text">
        <string>Temp High</string>
       </property>
      </widget>
     </item>
     <item row="5" column="0">
      <widget class="QLabel" name="label_5">
       <property name="text">
        <string>Temp Low</string>
       </property>
      </widget>
     </item>
     <item row="6" column="0">
      <widget class="QLabel" name="label_6">
       <property name="text">
        <string>Humidity</string>
       </property>
      </widget>
     </item>
     <item row="4" column="1">
      <widget class="QSpinBox" name="tempHiBox">
       <property name="minimum">
        <number>50</number>
       </property>
       <property name="maximum">
        <number>110</number>
       </property>
       <property name="singleStep">
        <number>1</number>
       </property>
       <property name="value">
        <number>77</number>
       </property>
      </widget>
     </item>
     <item row="5" column="1">
      <widget class="QSpinBox" name="tempLoBox">
       <property name="minimum">
        <number>50</number>
       </property>
       <property name="maximum">
        <number>110</number>
       </property>
       <property name="value">
        <number>77</number>
       </property>
      </widget>
     </item>
     <item row="6" column="1">
      <widget class="QSpinBox" name="humidBox">
       <property name="value">
        <number>50</number>
       </property>
      </widget>
     </item>
    </layout>
   </item>
   <item>
    <widget class="QGroupBox" name="imageGroup">
     <property name="title">
      <string>Images</string>
     </property>
     <layout class="QVBoxLayout" name="verticalLayout">
      <item>
       <widget class="QTableView" name="imageTable"/>
      </item>
      <item>
       <widget class="QPushButton" name="pushButton_2">
        <property name="text">
         <string>Remove Image</string>
        </property>
       </widget>
      </item>
     </layout>
    </widget>
   </item>
   <item>
    <widget class="QPushButton" name="addImageBtn">
     <property name="text">
      <string>Add Image</string>
     </property>
    </widget>
   </item>
   <item>
    <widget class="QDialogButtonBox" name="buttonBox">
     <property name="orientation">
      <enum>Qt::Horizontal</enum>
     </property>
     <property name="standardButtons">
      <set>QDialogButtonBox::Cancel|QDialogButtonBox::Ok</set>
     </property>
    </widget>
   </item>
  </layout>
 </widget>
 <resources/>
 <connections>
  <connection>
   <sender>buttonBox</sender>
   <signal>accepted()</signal>
   <receiver>Entry</receiver>
   <slot>accept()</slot>
   <hints>
    <hint type="sourcelabel">
     <x>248</x>
     <y>254</y>
    </hint>
    <hint type="destinationlabel">
     <x>157</x>
     <y>274</y>
    </hint>
   </hints>
  </connection>
  <connection>
   <sender>buttonBox</sender>
   <signal>rejected()</signal>
   <receiver>Entry</receiver>
   <slot>reject()</slot>
   <hints>
    <hint type="sourcelabel">
     <x>316</x>
     <y>260</y>
    </hint>
    <hint type="destinationlabel">
     <x>286</x>
     <y>274</y>
    </hint>
   </hints>
  </connection>
 </connections>
</ui>
